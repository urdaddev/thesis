import xarray as xr
import pandas as pd
import numpy as np
import json
rnc = xr.open_dataset("../../risk.nc")
rdf = rnc.to_dataframe()
stupid = []
colname = rdf.columns

for i in range(10):
    a = rdf[colname[i]].min()
    b = rdf[colname[i]].max()
    if a != b:
        steps = np.linspace(a, b, num=100)
        ll = np.arange(99)
        ll = ll.tolist()
        group = {"group": ll}

        for j in range(1, 99):
            group["group"].append(j)
            iid2 = rdf[(rdf[colname[i]] > steps[j]) & (
                rdf[colname[i]] < steps[j+1])].index
            isa=np.random.randint(len(iid2), size=100)
            group["group"][j] = iid2[isa]
      
        stupid.append(obj)

with open("row.json", "wb") as f:
    rapidjson.dump(stupid, f, ensure_ascii=True)
