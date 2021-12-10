import statsmodels.api as sm
from sklearn.ensemble import AdaBoostClassifier, GradientBoostingClassifier
from pprint import pprint

bacteria = sm.datasets.get_rdataset(dataname='bacteria', package='MASS')
# pprint(object=bacteria.data)
# pprint(object=type(bacteria.data))

pprint(bacteria.data.loc[:, 'y'])
pprint(bacteria.data.loc[:, not y])

# AdaBoost
adaboost_model = AdaBoostClassifier(n_estimators=10, algorithm='SAMME')
# adaboost_model.fit(X=bacteria.loc[:, 'y'], bacteria[:, ])

raise Exception


