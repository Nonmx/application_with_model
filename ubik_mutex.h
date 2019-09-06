/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the itf_ubinos component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/

#ifndef ITF_UBIK_MUTEX_H_
#define ITF_UBIK_MUTEX_H_

#ifdef	__cplusplus
extern "C" {
#endif

	/**
	 * @file ubik_mutex.h
	 *
	 * @brief ubik (Ubinos Kernel) ������Ʈ ���ؽ� �������̽�
	 */

	 /**
	  * @example	mutextest00.c
	  * @example	mutextest01.c
	  * @example	mutextest02.c
	  * @example	mutextest03.c
	  * @example	mutextest04.c
	  */

	  /**
	   * \page mutex_example ���ؽ� ����
	   *
	   *         \section mutextest00_sec ������ ���ؽ� ��� ����
	   *             Simple mutex example
	   *
	   *             - <a href="mutextest00_8c-example.html">mutextest00.c</a>
	   *
	   *             �� ������ ���� ���� �ΰ��� �����ȴ�.
	   *             ���� �������� ���� ������ �ϳ��� ���������� ����ϴ� �½�ũ�� �ΰ� �����Ѵ�.
	   *             ù ��° ���� ������ ��ȣ ������mutual exclusive�� �ƴ� ������� �����͸� ����ϸ�,
	   *             �� ��° ���� ������ ���ؽ��� �̿��� ��ȣ ������mutual exclusive ������� �����͸� ����Ѵ�.
	   *             �� ���� ������ ù ��° �½�ũ(�½�ũ 1)�� ����loop �ݺ� Ƚ�� ��ŭ  �����Ϳ� 1�� ���ϸ�,
	   *             �� ��° �½�ũ(�½�ũ 2)�� ����loop �ݺ� Ƚ�� ��ŭ �����Ϳ� 1�� ����.
	   *             �������� �ʱⰪ�� 0�̸�, �� �½�ũ�� ����loop �ݺ� Ƚ���� �����ϴ�.
	   *             ���� �������� �������� 0�̾�� �Ѵ�.
	   *             �׷��� ù ��° ���� ������ ���� ����race condition ������ �߻���Ų��. ���� �������� �������� 0�� �ƴ� ���� �ȴ�.
	   *             �� ��° ���� ������ ���ؽ��� �̿��� ��ȣ ������mutual exclusive ������� �����͸� ����ϱ� ������
	   *             ���� ����race condition ������ �߻���Ű�� �ʴ´�. ���� �������� �������� 0�� �ȴ�.<br>
	   *
	   * <br>
	   *
	   *         \section mutextest01_sec ���ؽ� �⺻ ��� ����
	   *             Test on basic functions of mutex
	   *
	   *             - <a href="mutextest01_8c-example.html">mutextest01.c</a>
	   *
	   *             �� ������ �Ʒ��� ������ ���ؽ��� �⺻ ��ɵ��� �����Ѵ�.
	   * <pre>
	   *     ��ױ� ���
	   *     ��� ���� ���
	   * </pre>
	   *
	   *             ���� 1���� �߰� �켱������ �½�ũ 2�� �����Ѵ�.<br>
	   *             �׸��� ������ �½�ũ 2�� ���ؽ��� ��ٴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 1���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 2���� ���� �켱������ �½�ũ 1�� �����Ѵ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 2���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 3���� �½�ũ 1�� ���ؽ� ��ױ⸦ �õ��Ѵ�.<br>
	   *             �׷��� ���ؽ��� �̹� �½�ũ 2�� ���� ��������Ƿ� �½�ũ 1�� ����(���blocked ���°� �ȴ�).<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 3���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 4���� �½�ũ 2�� ���ؽ� ��ױ⸦ �ٽ� �ѹ� �õ��Ѵ�.<br>
	   *             ���ؽ��� �̹� ���������, ��� �½�ũ�� �½�ũ 2 �ڽ��̹Ƿ� ���ؽ��� �� ��� �õ��� ����Ѵ�.<br>
	   *             ���� ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 4���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 5���� �½�ũ 2�� ���ؽ� ��� ������ �õ��Ѵ�.<br>
	   *             ���ؽ��� �½�ũ 2�� ���� �ι� �������.<br>
	   *             ���� �� �õ��� �����ϴ��� ���ؽ��� ������ ����� ���¿� �ӹ�����.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 5���� �½�ũ2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 6���� �½�ũ 2�� �ٽ� �ѹ� ���ؽ� ��� ������ �õ��Ѵ�.<br>
	   *             �׷��� ���ؽ��� ����� ���¿��� �����.<br>
	   *             ���ؽ��� ��� �����Ǹ� �½�ũ 1�� ���ؽ��� ��װ� �����.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 6���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 7���� �½�ũ 1�� ���ؽ��� ��� �����ϰ�, ���� 8���� �޸�sleep�� �õ��Ѵ�.<br>
	   *             �׷��� �½�ũ 2�� ����� ���ؽ��� ��ٴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 7���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 8�� �Ǹ� �½�ũ 1�� �޸�sleep �ð��� ���ؼ� �����.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 8���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 9���� �½�ũ 1�� ���� 10������ ���� �ð����� �ΰ� ���ؽ� ��ױ⸦ �õ��Ѵ�.<br>
	   *             �׷��� ���ؽ��� �̹� �½�ũ 2�� ���� ��������Ƿ� �½�ũ 1�� ����(���blocked ���°� �ȴ�).<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 9���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 10�� �Ǹ� �½�ũ 1�� ���� �ð��� ���ؼ� ���ؽ��� ����� ���ߴ��� �����.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 10���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 11���� �½�ũ 1�� ����ȴ�.<br>
	   *
	   *             ���� 12���� �½�ũ 2�� ���ؽ��� ��� �����ϰ� ����ȴ�.<br>
	   *
	   * <br>
	   *
	   *             \image html ubik_test_mutextest01.gif
	   *
	   * <br>
	   *
	   *         \section mutextest02_sec ���ؽ��� ���� �켱���� ����priority inversion ��Ȳ ����
	   *             Test for priority inversion situation by mutex
	   *
	   *             - <a href="mutextest02_8c-example.html">mutextest02.c</a>
	   *
	   *             �� ������ �켱���� ���priority inheritance Ư���� ��Ȱ��ȭ�� ���ؽ��� ����ؼ�
	   *             ���ؽ��� ���� �켱���� ����priority inversion ��Ȳ�� �����Ѵ�.<br>
	   *             �켱���� ���priority inheritance Ư���� ��Ȱ��ȭ�� ���ؽ���
	   *             ���ؽ� ���� �Լ� Ȯ����(mutex_create_ext �Լ�)��
	   *             �켱���� ���priority inheritance Ư�� ��Ȱ��ȭ ���� ����(MUTEX_OPT__NOPRIORITYINHERITANCE)��
	   *             �Բ� ȣ���ϸ� �����ȴ�.<br>
	   *
	   *             ���� 1���� ���� �켱������ �½�ũ 3�� �����Ѵ�.<br>
	   *             �׸��� ������ �½�ũ 3�� ���ؽ��� ��ٴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 1���� �½�ũ 3�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 2���� ���� �켱������ �½�ũ 1�� �����Ѵ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 2���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 3���� �½�ũ 1�� ���ؽ� ��ױ⸦ �õ��Ѵ�.<br>
	   *             �׷��� ���ؽ��� �̹� �½�ũ 3�� ���� ��������Ƿ� �½�ũ 1�� ����(���blocked ���°� �ȴ�).<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 3���� �½�ũ 3�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 4���� �߰� �켱������ �½�ũ 2�� �����Ѵ�.<br>
	   *             ������ �½�ũ 2�� �켱������ �½�ũ 3�� �켱�������� ����.<br>
	   *             ���� ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 4���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 5���� �½�ũ 2�� ����ȴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 5���� �½�ũ 3�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             <b>
	   *             �׷��� ������� ���������� ����Ǿ����� ���� 4�� 5 ������ ��Ȳ�� �̻��ϴ�.
	   *             �½�ũ 2�� �켱������ �� ���� �½�ũ 1���� ���� ����Ǿ���.
	   *             �̿� �ռ� �߻��� �½�ũ 3�� �½�ũ 1���� ���� ����Ǵ� ��Ȳ��
	   *             �½�ũ 1�� �½�ũ 3�� ���� �ڿ�(���ؽ�)�� �ʿ�� �ϱ� ������ �߻��ϴ� ��¿ �� ���� ��Ȳ�̴�.
	   *             �׷��� �½�ũ 2�� �½�ũ 1�� �ƹ��� ���谡 ����.
	   *             �׷����� �ұ��ϰ� �½�ũ 2�� �켱������ �� ���� �½�ũ 1���� ���� ����Ǿ���.
	   *             �� �̻��� ��Ȳ�� �켱���� ����priority inversion ��Ȳ�̶� �Ҹ���, ���� ��Ȳ���� ���� �ȴ�.<br>
	   *             </b>
	   *
	   *             ���� 6���� �½�ũ 3�� ���ظ� ��� �����Ѵ�.<br>
	   *             �׷��� �½�ũ 1�� ���ؽ��� ��װ�  �����.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 6���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 7���� �½�ũ 1�� ���ؽ��� ��� �����ϰ� ����ȴ�.<br>
	   *
	   *             ���� 8���� �½�ũ 3�� ����ȴ�.<br>
	   *
	   * <br>
	   *
	   *             \image html ubik_test_mutextest02.gif
	   *
	   * <br>
	   *
	   *         \section mutextest03_sec �켱���� ����priority inversion ��Ȳ�� �����ϴ� ���ؽ��� �켱���� ���priority inheritance Ư�� ����
	   *             Test on priority inheritance feature of mutex preventing priority inversion situation
	   *
	   *             - <a href="mutextest03_8c-example.html">mutextest03.c</a>
	   *
	   *             �� ������ �켱���� ����priority inversion ��Ȳ�� �����ϴ� ���ؽ��� �켱���� ���priority inheritance Ư���� �����Ѵ�.<br>
	   *
	   *             ���� 1�������� �켱������ �½�ũ 3�� �����Ѵ�.<br>
	   *             �׸��� ������ �½�ũ 3�� ���ؽ��� ��ٴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 1���� �½�ũ 3�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 2���� ���� �켱������ �½�ũ 1�� �����Ѵ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 2���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 3���� �½�ũ 1�� ���ؽ� ��ױ⸦ �õ��Ѵ�.<br>
	   *             �׷��� ���ؽ��� �̹� �½�ũ 3�� ���� ��������Ƿ� �½�ũ 1�� ����(���blocked ���°� �ȴ�).<br>
	   *             �׸��� �½�ũ 3�� �½�ũ 1�� �켱������ ��� �޴´�. (�½�ũ 3�� �켱������ �½�ũ 1�� �켱������ ��������.)<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 3���� �½�ũ 3�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 4���� �߰� �켱������ �½�ũ 2�� �����Ѵ�.<br>
	   *             �½�ũ 3�� �½�ũ 1�� �켱������ ��� �޾ұ� ������ �½�ũ 3�� �켱������ �½�ũ 2�� �켱�������� ����.<br>
	   *             ���� ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 4���� �½�ũ 3�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             <b>
	   *             ���ؽ��� ���� �켱���� ����priority inversion ��Ȳ ���� ���������� �� ��������
	   *             �켱���� ����priority inversion ��Ȳ�� �߻��ߴ�.
	   *             �׷��� �� ���������� �켱���� ���priority inheritance Ư���� ���� ���ؽ��� ����ϱ� ������
	   *             �׷��� ���� ��Ȳ�� �߻����� �ʴ´�.<br>
	   *             </b>
	   *
	   *             ���� 5���� �½�ũ 3�� ���ؽ��� ��� ���� �Ѵ�.<br>
	   *             �׷��� �½�ũ 1�� ���ؽ��� ��װ� �����.<br>
	   *             �׸��� �½�ũ 3�� �켱������ ���� �켱������ ���� �ȴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 5���� �½�ũ 1�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 6���� �½�ũ 1�� ���ؽ��� ��� �����ϰ� ����ȴ�.<br>
	   *             ������� ���������� ����Ǿ��ٸ� Ȯ�� ���� 6���� �½�ũ 2�� ���� ���̾�� �Ѵ�.<br>
	   *
	   *             ���� 7���� �½�ũ 2�� ����ȴ�.<br>
	   *
	   *             ���� 8���� �½�ũ 3�� ����ȴ�.<br>
	   *
	   * <br>
	   *
	   *             \image html ubik_test_mutextest03.gif
	   *
	   * <br>
	   *
	   *         \section mutextest04_sec ���ؽ��� ���� �޸� ���� ����
	   *             Test for memory leak by mutex
	   *
	   *             - <a href="mutextest04_8c-example.html">mutextest04.c</a>
	   *
	   *             �� ������ ���ؽ��� ���� �޸� ������ �����Ѵ�.<br>
	   *             ���� ������ ������ ����.<br>
	   *
	   *             ���� ��heap�� �Ҵ�� �޸� �ѷ��� �޸� ���� ���� ������ �����Ѵ�.<br>
	   *             �׸��� ���ؽ� ������ ���Ÿ� ���� �� �ݺ��Ѵ�.<br>
	   *             �� ���� ��heap�� �Ҵ�� �޸� �ѷ��� �޸� ���� ���� �ٽ� ������ �����ߴ� ���� ���Ѵ�.<br>
	   *             �޸� ������ �߻����� �ʾҴٸ� �����ߴ� ���� �ٽ� ������ ���� ���ƾ� �Ѵ�.<br>
	   *
	   * <br>
	   *
	   * Content is available under Attribution-Noncommercial-No Derivative Works 3.0 Unported.
	   */

	   //#include "type.h"

			  /** ���ؽ� ���� ����: ���ؽ��� �켱���� ���priority inheritance Ư���� ��Ȱ��ȭ �� (�켱���� ���priority inheritance Ư�� ��Ȱ��ȭ ���� ����) */
#define	MUTEX_OPT__NOPRIORITYINHERITANCE	0x80

	// ys modified
	/*typedef	struct __mutex_tip_t {
		unsigned int		type : 8;
		unsigned int		valid : 1;
		unsigned int		reserved : 7;

		unsigned int		reserved2 : 16;
	} _mutex_tip_t;*/

	/** ���ؽ� ������ �� ���� */

	//ys modified
	//typedef	_mutex_tip_t* mutex_pt;

	/**
	 * ���ؽ��� �����ϴ� �Լ�
	 *
	 * @param	mutex_p		������ ���ؽ��� �ּҸ� ������ �������� �ּ�<br>
	 * 						<br>
	 *
	 * @return	  0: ����<br>
	 * 			<br>
	 * 			 -1: ����<br>
	 * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
	 */
	 //ys modified
	 //int mutex_create(mutex_pt* mutex_p);

	 /**
	  * ���ؽ��� �����ϴ� �Լ� Ȯ����
	  *
	  * @param	mutex_p		������ ���ؽ��� �ּҸ� ������ �������� �ּ�<br>
	  * 						<br>
	  *
	  * @param	option		���� ���� (MUTEX_OPT__...)<br>
	  * 						0: ��� �͵� �������� ����<br>
	  * 						<br>
	  *
	  * @return	  0: ����<br>
	  * 			<br>
	  * 			 -1: ����<br>
	  * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
	  */
	int mutex_create_ext(mutex_pt * mutex_p, unsigned int option);

	/**
	 * ��� ���ؽ��� �����ϴ� �Լ�
	 *
	 * @param	mutex_p		������ ��� ���ؽ��� �ּҰ� ����� �������� �ּ�<br>
	 * 						<br>
	 * 						���ſ� �����ϸ� *mutex_p�� NULL�� ��<br>
	 * 						<br>
	 *
	 * @return	  0: ����<br>
	 * 			<br>
	 * 			 -1: ����<br>
	 * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
	 */

	 // ys modified
	 //int mutex_delete(mutex_pt* mutex_p);

	 /**
	  * ��� ���ؽ��� ��״� �Լ�
	  *
	  * @param	mutex		��� ���ؽ� ������<br>
	  * 						<br>
	  *
	  * @return	  0: ����<br>
	  * 			<br>
	  * 			 -1: ����<br>
	  * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
	  * 			UBIK_ERR__DEADLOCK		: ����� �߻� ���ɼ��� ����<br>
	  * 			UBIK_ERR__TERMINATED	: ��ٸ��� ��ü�� ���ŵǾ���<br>
	  */

	  //ys modified
	  //int mutex_lock(mutex_pt mutex);

	  /**
	   * ���� �ð��� �ΰ� ��� ���ؽ� ��ױ⸦ �õ��ϴ� �Լ�
	   *
	   * @param	mutex		��� ���ؽ� ������<br>
	   * 						<br>
	   *
	   * @param	tick		���� �ð� (�ý��� ƽtick ��)<br>
	   * 						<br>
	   *
	   * @return	  0: ����<br>
	   * 			<br>
	   * 			 -1: ����<br>
	   * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
	   * 			UBIK_ERR__TIMEOUT		: ���� �ð� �ʰ�<br>
	   * 			UBIK_ERR__DEADLOCK		: ����� �߻� ���ɼ��� ����<br>
	   * 			UBIK_ERR__TERMINATED	: ��ٸ��� ��ü�� ���ŵǾ���<br>
	   */

	   //ys modified
	   //int mutex_lock_timed(mutex_pt mutex, unsigned int tick);

	   /**
		* ���� �ð��� �ΰ� ��� ���ؽ� ��ױ⸦ �õ��ϴ� �Լ� (õ���� ���� ����)
		*
		* @param	mutex		��� ���ؽ� ������<br>
		* 						<br>
		*
		* @param	timems		���� �ð� (õ���� ����)<br>
		* 						<br>
		*
		* @return	  0: ����<br>
		* 			<br>
		* 			 -1: ����<br>
		* 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
		* 			UBIK_ERR__TIMEOUT		: ���� �ð� �ʰ�<br>
		* 			UBIK_ERR__DEADLOCK		: ����� �߻� ���ɼ��� ����<br>
		* 			UBIK_ERR__TERMINATED	: ��ٸ��� ��ü�� ���ŵǾ���<br>
		*/

		//ys modified
		//int mutex_lock_timedms(mutex_pt mutex, unsigned int timems);

		/**
		 * ��� ���ؽ��� ��� �����ϴ� �Լ�
		 *
		 * @param	mutex		��� ���ؽ� ������<br>
		 * 						<br>
		 *
		 * @return	  0: ����<br>
		 * 			<br>
		 * 			 -1: ����<br>
		 * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
		 */

		 //ys modified
		 //int mutex_unlock(mutex_pt mutex);

		 /**
		  * ���ؽ��� ����� �ִ��� ���θ� �����ִ� �Լ�
		  *
		  * @param	mutex		��� ���ؽ� ������<br>
		  * 						<br>
		  *
		  * @return	  1: ����� ����<br>
		  *            0: �����  ���� ����<br>
		  * 			<br>
		  * 			 -1: ����<br>
		  * 			 -n: n-1 ��° �Ű������� �߸��Ǿ���<br>
		  */


		  //ys modified
		  //int mutex_islocked(mutex_pt mutex);

#ifdef	__cplusplus
}
#endif

#endif /* ITF_UBIK_MUTEX_H_ */
