#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ��������
void CountSort(vector<int>& vecRaw, vector<int>& vecObj)
{
	// ȷ�������������ǿ�
	if (vecRaw.size() == 0)
		return;

	// ʹ�� vecRaw �����ֵ + 1 ��Ϊ�������� countVec �Ĵ�С
	int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
	vector<int> vecCount(vecCountLength, 0);

	// ͳ��ÿ����ֵ���ֵĴ���
	for (int i = 0; i < vecRaw.size(); i++)
		vecCount[vecRaw[i]]++;

	// ����ļ�ֵ���ֵ�λ��Ϊǰ�����м�ֵ���ֵĴ���֮��
	for (int i = 1; i < vecCountLength; i++)
		vecCount[i] += vecCount[i - 1];

	// ����ֵ�ŵ�Ŀ��λ��
	for (int i = vecRaw.size(); i > 0; i--)	// �˴�������Ϊ�˱�����ͬ��ֵ���ȶ���
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];
}

int main()
{
	vector<int> vecRaw = { 0,5,7,9,6,3,4,5,2,8,6,9,2,1 };
	vector<int> vecObj(vecRaw.size(), 0);

	CountSort(vecRaw, vecObj);

	for (int i = 0; i < vecObj.size(); ++i)
		cout << vecObj[i] << "  ";
	cout << endl;

	return 0;
}