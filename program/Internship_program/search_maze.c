/*------------------------------------------------------------------------------*/
/* Include Files								*/
/*------------------------------------------------------------------------------*/
#include "search_maze.h"

/*------------------------------------------------------------------------------*/
/* Global Variable								*/
/*------------------------------------------------------------------------------*/
t_position	g_Position;
t_wall		g_Wall[MAZESIZE_X][MAZESIZE_Y];		// ���H�̕Ǐ����i�[����\���̔z��
t_mapFlag 	g_MapFlag[MAZESIZE_X][MAZESIZE_Y];	// �S�Ẵ}�X�̑�����ێ�����z��
unsigned int	g_Map[MAZESIZE_X][MAZESIZE_Y];		// �����}�b�v�p�̔z��
unsigned int	g_MapSearched[MAZESIZE_X][MAZESIZE_Y];	// �����}�b�v�p�̔z��

/*------------------------------------------------------------------------------*/
/* Function Definitions								*/
/*------------------------------------------------------------------------------*/
void init_maze(void);
void search_all_maze(int goal_x, int goal_y);
void create_map(int x_coordinate, int y_coordinate);
void init_map(int x_coordinate, int y_coordinate);
int get_priority(int x_coordinate, int y_coordinate, t_direction dir);
int judgment_nextdir(int x_coordinate, int y_coordinate, t_direction *next_dir);
void set_wall(int x_coordinate, int y_coordinate);
t_bool get_unexplores(int *x_coordinate, int *y_coordinate);

extern void tire_control(int rotation_direction_R, int rotation_direction_L, int drive_distance);
extern void go_rotate(int drive_distance, int rotation_direction_R, int rotation_direction_L);
extern void go_straight(int drive_distance, float tar_speed);
/*==============================================================================*/
/*  ���H���̏�����			                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_maze(void)
{
	int x,y;
	
	/* ���H�̑S�̂̕Ǐ��𖢒�`�ɐݒ� */
	for(x = 0; x < MAZESIZE_X; x++)
	{
		for(y = 0; y < MAZESIZE_Y; y++)
		{
			
			g_Wall[x][y].north = UNKNOWN;
			g_Wall[x][y].east  = UNKNOWN;
			g_Wall[x][y].south = UNKNOWN;
			g_Wall[x][y].west  = UNKNOWN;
			
			g_MapSearched[x][y] = UNEXPLORED;	// �S�č��W�𖢒T���ɃZ�b�g
		}
	}
	
	/* ���H�̎l���̊O�Ǐ��̐ݒ� */
	for(x = 0; x < MAZESIZE_X; x++)
	{
		g_Wall[x][0].south = WALL;		// �l���̕ǂ�ǉ�����(��)
		g_Wall[x][MAZESIZE_Y-1].north = WALL;	// �l���̕ǂ�ǉ�����(�k)
	}
	for(y = 0; y < MAZESIZE_Y; y++)
	{
		g_Wall[0][y].west = WALL;		// �l���̕ǂ�ǉ�����(��)
		g_Wall[MAZESIZE_X-1][y].east = WALL;	// �l���̕ǂ�ǉ�����(��)
	}
	
	/* �X�^�[�g�n�_(�������W(0,0))�̕Ǐ��̐ݒ� */
	g_Wall[0][0].east = WALL;				// �X�^�[�g�n�_�̉E�̕ǂ�ǉ�����
	g_Wall[1][0].west = WALL;
	g_MapSearched[0][0] = EXPLORED;
}
/*==============================================================================*/
/* ���H�̑S�T��				                                        */
/* 										*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void search_all_maze(int goal_x, int goal_y)
{
	
	/* �T�����x�̐ݒ� */
	accel = SEARCH_ACCEL;
		
	/* �����ʒu(0,0)���玟�ɍs�������𔻒� */
	t_direction next_direction;

	int next_drive;
	
	next_drive = judgment_nextdir(goal_x, goal_y, &next_direction);
	
	/* ���肵�������ɐi�� */
	switch(next_drive)
	{
		case north:
			//straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			go_straight(STRAIGHT_HALFSECTION, SEARCH_SPEED);		// 0.5���i��
			//g_Position.y++;							// �k������������Y���W�𑝂₷
			break;
		case east:
			//rotate(right,1);
			//straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			go_rotate(TURN_90,MOT_BACK, MOT_FORWARD);			// �E��90�x����
			//g_Position.x++;							// ��������������X���W�𑝂₷
			break;
		case south:
			//rotate(left,2);
			//straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			go_rotate(TURN_180,MOT_BACK, MOT_FORWARD);			// ���Ɍ���(180�x�^�[��)
			//g_Position.y--;							// �������������Y���W�����炷
			break;
		case west:
			rotate(left,1);
			straight(STRAIGHT_HALFSECTION,0,SEARCH_SPEED,SEARCH_SPEED);
			//go_rotate(TURN_90,MOT_FORWARD, MOT_BACK);			// ����90�x����
			//g_Position.x--;							// �����������Ƃ���X���W�����炷
			break;
	}
	
	g_Position.dir = next_direction;	// �������X�V
	
	switch(g_Position.dir)
	{
		case north:
			g_Position.y++;							// �k������������Y���W�𑝂₷
			break;
		case east:
			g_Position.x++;							// ��������������X���W�𑝂₷
			break;
		case south:
			g_Position.y--;							// �������������Y���W�����炷
			break;
		case west:
			g_Position.x--;							// �����������Ƃ���X���W�����炷
			break;
	}

	
	/* �S�[�����W(goal_x, goal_y)�Ɍ������Ė��H�T�� */
	while( (g_Position.x != goal_x) || (g_Position.y != goal_y))
	{
		set_wall(g_Position.x, g_Position.y);			// �Ǐ����Z�b�g
		
		/* ���ɍs�������𔻒� */
		next_drive = judgment_nextdir(goal_x, goal_y, &next_direction);
	
		/* ���肵�������ɐi�� */
		switch(next_drive)
		{
			case north:
				go_straight(STRAIGHT_SECTION, SEARCH_SPEED);			// 1���i��
				//g_Position.y++;							// �k������������Y���W�𑝂₷
				break;
			case east:
				tire_control(MOT_BACK, MOT_FORWARD, TURN_90);			// �E��90�x����
				//g_Position.x++;							// ��������������X���W�𑝂₷
				break;
			case south:
				tire_control(MOT_BACK, MOT_FORWARD, TURN_180);			// ���Ɍ���(180�x�^�[��)
				//g_Position.y--;							// �������������Y���W�����炷
				break;
			case west:
				tire_control(MOT_FORWARD, MOT_BACK, TURN_90);			// ����90�x����
				//g_Position.x--;							// �����������Ƃ���X���W�����炷
				break;
		}
		
		g_Position.dir = next_direction;	// �������X�V
		
		switch(g_Position.dir)
		{
			case north:
				g_Position.y++;							// �k������������Y���W�𑝂₷
				break;
			case east:
				g_Position.x++;							// ��������������X���W�𑝂₷
				break;
			case south:
				g_Position.y--;							// �������������Y���W�����炷
				break;
			case west:
				g_Position.x--;							// �����������Ƃ���X���W�����炷
				break;
		}
	}
	
	set_wall(g_Position.x,g_Position.y);				// �Ǐ����Z�b�g
	go_straight(STRAIGHT_HALFSECTION, MIN_SPEED);			// �S�[��.�@0.5���i��
}
/*==============================================================================*/
/* �i�s���p����				                                        */
/* 										*/
/* �ڕW(�S�[��)���WX,Y�Ɍ������ꍇ�A���ɍs���ׂ������𔻒肷��			*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate		�ڕW(�S�[��)�ʒu��X���W		*/
/*			y_coordinate		�ڕW(�S�[��)�ʒu��Y���W		*/
/*			next_dir		���ɍs���ׂ�����		*/
/*  Return   :         	judgment_nextdir	�i�s����			*/
/*==============================================================================*/
int judgment_nextdir(int x_coordinate, int y_coordinate, t_direction *next_dir)	
{
	int priority	 = 0;		// �i�s�����̗D��x
	int tmp_priority = 0;		// �i�s�����̗D��x(�ꎞ�I)
	int min_step	 = 255;		// �ŏ�������255��(map��unsigned char�^�Ȃ̂�)�ɐݒ�
	
	/* �����}�b�v�̍쐬 */
	create_map(x_coordinate, y_coordinate);
		
	/* �s���ׂ������̔��� */
	if((g_Wall[g_Position.x][g_Position.y].north & MASK_SEARCH) == NOWALL)	// �k�ɕǂ��Ȃ����
	{
		tmp_priority = get_priority(g_Position.x, g_Position.y + 1, north);	// �D��x���Z�o
		if(g_Map[g_Position.x][g_Position.y+1] < min_step)			// ��ԕ�����������������������
		{
			min_step = g_Map[g_Position.x][g_Position.y+1];			// �ЂƂ܂��k�����������������ɂ���
			*next_dir = north;						// ������ۑ�
			priority = tmp_priority;					// �D��x��ۑ�
		}
		else if(g_Map[g_Position.x][g_Position.y+1] == min_step)		// �����������ꍇ�͗D��x���画�f����
		{
			if(priority < tmp_priority )		// �D��x��]��
			{
				*next_dir = north;		// �������X�V
				priority = tmp_priority;	// �D��x��ۑ�
			}
		}
	}
	
	if((g_Wall[g_Position.x][g_Position.y].east & MASK_SEARCH) == NOWALL)	// ���ɕǂ��Ȃ����
	{
		tmp_priority = get_priority(g_Position.x + 1, g_Position.y, east);	// �D��x���Z�o
		if(g_Map[g_Position.x + 1][g_Position.y] < min_step)			// ��ԕ�����������������������
		{
			min_step = g_Map[g_Position.x+1][g_Position.y];			// �ЂƂ܂��������������������ɂ���
			*next_dir = east;						// ������ۑ�
			priority = tmp_priority;					// �D��x��ۑ�
		}
		else if(g_Map[g_Position.x + 1][g_Position.y] == min_step)		// �����������ꍇ�A�D��x���画�f
		{
			if(priority < tmp_priority)		// �D��x��]��
			{
				*next_dir = east;		// ������ۑ�
				priority = tmp_priority;	// �D��x��ۑ�
			}
		}
	}
	
	if((g_Wall[g_Position.x][g_Position.y].south & MASK_SEARCH) == NOWALL)	// ��ɕǂ��Ȃ����
	{
		tmp_priority = get_priority(g_Position.x, g_Position.y - 1, south);	// �D��x���Z�o
		if(g_Map[g_Position.x][g_Position.y - 1] < min_step)			// ��ԕ�����������������������
		{
			min_step = g_Map[g_Position.x][g_Position.y-1];			// �ЂƂ܂��삪���������������ɂ���
			*next_dir = south;						// ������ۑ�
			priority = tmp_priority;					// �D��x��ۑ�
		}
		else if(g_Map[g_Position.x][g_Position.y - 1] == min_step)		// �����������ꍇ�A�D��x�ŕ]��
		{
			if(priority < tmp_priority)		// �D��x��]��
			{
				*next_dir = south;		// ������ۑ�
				priority = tmp_priority;	// �D��x��ۑ�
			}
		}
	}
	
	if((g_Wall[g_Position.x][g_Position.y].west & MASK_SEARCH) == NOWALL)	// ���ɕǂ��Ȃ����
	{
		tmp_priority = get_priority(g_Position.x - 1, g_Position.y, west);	// �D��x���Z�o
		if(g_Map[g_Position.x-1][g_Position.y] < min_step)			// ��ԕ�����������������������
		{
			min_step = g_Map[g_Position.x-1][g_Position.y];			// ����������������
			*next_dir = west;						// ������ۑ�
			priority = tmp_priority;					// �D��x��ۑ�
		}
		else if(g_Map[g_Position.x - 1][g_Position.y] == min_step)		// �����������ꍇ�A�D��x�ŕ]��
		{
			*next_dir = west;			// ������ۑ�
			priority = tmp_priority;		// �D��x��ۑ�
		}
	}

	return ( (int)((4 + *next_dir - g_Position.dir) % 4) );
}

/*==============================================================================*/
/* �D��x�Z�o				                                        */
/* 										*/
/* ���WX,Y�ƁA�����Ă�����pdir����D��x���Z�o����				*/
/*   �E���T������ԗD��x������.(4)						*/
/*   �E�����̌����ƍs��������������A�O(2)��(1)��(0)�Ƃ��ėD��x��t������	*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	�ڕW(�S�[��)�ʒu��X���W		       	*/
/*			y_coordinate	�ڕW(�S�[��)�ʒu��Y���W			*/
/*			dir		���݌����Ă�����p			*/
/*  Return   :         	get_priority	�D��x(0�`4)				*/
/*==============================================================================*/
int get_priority(int x_coordinate, int y_coordinate, t_direction dir)
{	
	int priority = 0;	// �D��x���L�^����ϐ�

	/* �D��x�Z�o */
	if(g_Position.dir == dir)			// �s���������������݂̐i�s�����Ɠ����ꍇ
	{
		priority = 2;	// �O
	}
	else if( ((4+g_Position.dir-dir)%4) == 2)	// �s���������������݂̐i�s�����Ƌt�̏ꍇ
	{
		priority = 0;	// ��
	}
	else						// ����ȊO(���E�ǂ��炩)�̏ꍇ
	{
		priority = 1;	// ��
	}
	
	if(	(g_Wall[x_coordinate][y_coordinate].north == UNKNOWN) 		// �ǂ����̕Ǐ�񂪕s���̂܂܂ł����
	     || (g_Wall[x_coordinate][y_coordinate].east  == UNKNOWN)
	     || (g_Wall[x_coordinate][y_coordinate].south == UNKNOWN)
	     || (g_Wall[x_coordinate][y_coordinate].west  == UNKNOWN))
	{
		priority += 4;	// ���T���̏ꍇ�A�D��x������ɕt��
	}
	
	return priority;
}

/*==============================================================================*/
/* �����}�b�v�̍쐬			                                        */
/* 										*/
/* ���WX,Y���S�[���Ƃ��������}�b�v���쐬����					*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	�ڕW(�S�[��)�ʒu��X���W		       	*/
/*			y_coordinate	�ڕW(�S�[��)�ʒu��Y���W			*/
/*  Return   :         	-							*/
/*==============================================================================*/
void create_map(int x_coordinate, int y_coordinate)
{
	int x,y;
	t_bool change_flag;	// Map�쐬�I�������ɂ߂邽�߂̃t���O
	
	/* �����}�b�v�̏����� */
	init_map(x_coordinate, y_coordinate);
	
	do
	{
		change_flag = false;
		// �ύX���Ȃ������ꍇ�ɂ̓��[�v�𔲂���
		
		/* ���H�̑傫�������[�v(X���W,Y���W) */
		for(x = 0; x < MAZESIZE_X; x++)
		{
			for(y = 0; y < MAZESIZE_Y; y++)
			{
				if(g_Map[x][y] == UNEXPLORED)	// ���T���̏ꍇ�͎���
				{
					continue;
				}
				
				if(y < MAZESIZE_Y-1)				// �k�F�͈̓`�F�b�N
				{
					if((g_Wall[x][y].north & MASK_SEARCH) == NOWALL)	// �ǂ��Ȃ����
					{
						if(g_Map[x][y+1] == UNEXPLORED)			// �܂��l�������Ă��Ȃ����
						{
							g_Map[x][y+1] = g_Map[x][y] + 1;	// �l����
							change_flag = true;			// �l���X�V���ꂽ���Ƃ�����
						}
					}
				}
			
				if(x < MAZESIZE_X-1)				// ���F�͈̓`�F�b�N
				{
					if((g_Wall[x][y].east & MASK_SEARCH) == NOWALL)		// �ǂ��Ȃ����
					{
						if(g_Map[x+1][y] == UNEXPLORED)			// �܂��l�������Ă��Ȃ����
						{
							g_Map[x+1][y] = g_Map[x][y] + 1;	// �l����
							change_flag = true;			// �l���X�V���ꂽ���Ƃ�����
						}
					}
				}
			
				if(y > 0)					// ��F�͈̓`�F�b�N
				{
					if((g_Wall[x][y].south & MASK_SEARCH) == NOWALL)	// �ǂ��Ȃ����
					{
						if(g_Map[x][y-1] == UNEXPLORED)			// �܂��l�������Ă��Ȃ����
						{
							g_Map[x][y-1] = g_Map[x][y] + 1;	// �l����
							change_flag = true;			// �l���X�V���ꂽ���Ƃ�����
						}
					}
				}
			
				if(x > 0)					// ���F�͈̓`�F�b�N
				{
					if((g_Wall[x][y].west & MASK_SEARCH) == NOWALL)		// �ǂ��Ȃ����
					{
						if(g_Map[x-1][y] == UNEXPLORED)			// �܂��l�������Ă��Ȃ����
						{
							g_Map[x-1][y] = g_Map[x][y] + 1;	// �l����	
							change_flag = true;			// �l���X�V���ꂽ���Ƃ�����
						}
					}
				}	
			}
		}
	}while(change_flag == true);	// �S�̂����I���܂ő҂�	
}

/*==============================================================================*/
/* �����}�b�v�̏�����			                                        */
/* 										*/
/* �����}�b�v������������B�S�̂�0xff�A�����̍��WX,Y��0�ŏ���������		*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		-						       	*/
/*  Return   :         	-							*/
/*==============================================================================*/
void init_map(int x_coordinate, int y_coordinate)
{
	int x,y;
	
	/* ���H�̑傫�������[�v(X���W,Y���W) */
	for(x = 0; x < MAZESIZE_X; x++)				
	{
		for(y = 0; y < MAZESIZE_Y; y++)
		{
			g_Map[x][y] = UNEXPLORED;	// ���ׂ�255�Ŗ��߂�(0xff)
		}
	}
	
	/* �S�[�����W�̕�����0�ɐݒ� */
	g_Map[x_coordinate][y_coordinate] = 0;
}

/*==============================================================================*/
/* �Ǐ��̋L�^				                                        */
/* 										*/
/* �����̍��WX,Y�ɕǏ�����������						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	�ڕW�ʒu��X���W		       		*/
/*			y_coordinate	�ڕW�ʒu��Y���W				*/
/*  Return   :         	-							*/
/*==============================================================================*/
void set_wall(int x_coordinate, int y_coordinate)
{
	/* �Ǐ��ɏ������ރf�[�^ */
	int n_write;	// �k
	int s_write;	// ��
	int e_write;	// ��
	int w_write;	// ��
	
	/* �����̕����ɉ����ď������ރf�[�^�𐶐� */
	switch(g_Position.dir){
		case north:	// �k�������Ă��鎞
			n_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// �O�ǂ̗L���𔻒f
			e_write = CONV_SEN2WALL(sen_r.is_wall);				// �E�ǂ̗L���𔻒f
			w_write = CONV_SEN2WALL(sen_l.is_wall);				// ���ǂ̗L���𔻒f
			s_write = NOWALL;						// ���͕K���ǂ��Ȃ�
			break;
			
		case east:	// ���������Ă���Ƃ�
			e_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// �O�ǂ̗L���𔻒f
			s_write = CONV_SEN2WALL(sen_r.is_wall);				// �E�ǂ̗L���𔻒f
			n_write = CONV_SEN2WALL(sen_l.is_wall);				// ���ǂ̗L���𔻒f
			w_write = NOWALL;						// ���͕K���ǂ��Ȃ�
			break;
			
		case south:	// ��������Ă���Ƃ�
			s_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// �O�ǂ̗L���𔻒f
			w_write = CONV_SEN2WALL(sen_r.is_wall);				// �E�ǂ̗L���𔻒f
			e_write = CONV_SEN2WALL(sen_l.is_wall);				// ���ǂ̗L���𔻒f
			n_write = NOWALL;						// ���͕K���ǂ��Ȃ�
			break;
			
		case west:	// ���������Ă���Ƃ�
			w_write = CONV_SEN2WALL(sen_fr.is_wall || sen_fl.is_wall);	// �O�ǂ̗L���𔻒f
			n_write = CONV_SEN2WALL(sen_r.is_wall);				// �E�ǂ̗L���𔻒f
			s_write = CONV_SEN2WALL(sen_l.is_wall);				// ���ǂ̗L���𔻒f
			e_write = NOWALL;						// ���͕K���ǂ��Ȃ�
			break;
	}
	
	/* �Ǐ��̏������� */
	g_Wall[x_coordinate][y_coordinate].north = n_write;	
	g_Wall[x_coordinate][y_coordinate].south = s_write;
	g_Wall[x_coordinate][y_coordinate].east  = e_write;
	g_Wall[x_coordinate][y_coordinate].west  = w_write;
	
	/* ���Α����猩���Ǐ����������� */
	if(y_coordinate < MAZESIZE_Y-1)		// �͈̓`�F�b�N
	{
		g_Wall[x_coordinate][y_coordinate+1].south = n_write;	// ���Α����猩���ǂ���������
	}
	
	if(x_coordinate < MAZESIZE_X-1)		// �͈̓`�F�b�N
	{
		g_Wall[x_coordinate+1][y_coordinate].west = e_write;	// ���Α����猩���ǂ���������
	}
	
	if(y_coordinate > 0)			// �͈̓`�F�b�N
	{
		g_Wall[x_coordinate][y_coordinate-1].north = s_write;	// ���Α����猩���ǂ���������
	}
	
	if(x_coordinate > 0)			// �͈̓`�F�b�N
	{
		g_Wall[x_coordinate-1][y_coordinate].east = w_write;	// ���Α����猩���ǂ���������
	}
	
	/* �T�����W�̋L�^ */
	g_MapSearched[x_coordinate][y_coordinate] = EXPLORED;
}

/*==============================================================================*/
/* ���T�����W�̎擾			                                        */
/* 										*/
/* ���T���̍��W��������X,Y�ɏ�������						*/
/* ---------------------------------------------------------------------------- */
/*  Arguments:		x_coordinate	�ڕW�ʒu��X���W		       		*/
/*			y_coordinate	�ڕW�ʒu��Y���W				*/
/*  Return   :         	true		���T�����W�L				*/
/*			false		���T�����W��				*/
/*==============================================================================*/
t_bool get_unexplores(int *x_coordinate, int *y_coordinate)
{
	int x,y;
	t_bool get_result = false;	// ���T�����W�擾����
	
	/* ���H�̑傫�������[�v(X���W,Y���W) */
	for(x = 0; x < MAZESIZE_X; x++)				
	{
		if(get_result == true)	/* �ŏ��Ɍ��������T�����W�����ʂƂ��ĕԂ� */
		{
			break;
		}
		
		for(y = 0; y < MAZESIZE_Y; y++)
		{
			if(g_MapSearched[x][y] == UNEXPLORED)
			{
				*x_coordinate = x;
				*y_coordinate = y;
				get_result    = true;
				break;
			}
		}
	}
	
	return get_result;
}