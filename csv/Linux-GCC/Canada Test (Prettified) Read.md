
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1992.79 | 0.133028 | 8027.09ms | 5373214 | 30 | 3.51038e+08 | 2.57141e+06 | 0.0969848 | 2.54418 | 13.7654 | 2.865 | 0.00567397 | 0.038532 | 0.000120071 | 1(Win) | true |
| Jsonifier (two-stage) | 1898.03 | 0.1248 | 8367.04ms | 5373214 | 40 | 4.54101e+08 | 2.69979e+06 | 0.102657 | 2.65863 | 13.9912 | 2.70406 | 0.00702365 | 0.0626048 | 0.00201908 | 2(Loss) | true |
| simdjson (reflection) | 1883.8 | 0.144045 | 8451.74ms | 5373214 | 40 | 6.14123e+08 | 2.72019e+06 | 0.0651701 | 2.67878 | 12.9387 | 2.26858 | 0.00468605 | 0.061363 | 0.000519996 | 3(Loss) | true |
| simdjson (ondemand) | 1714.46 | 0.0548741 | 9290.75ms | 5373214 | 80 | 2.15197e+08 | 2.98886e+06 | 0.0549539 | 2.94489 | 13.642 | 2.49411 | 0.00628621 | 0.0649196 | 0.000207646 | 4(Loss) | true |
| Glaze | 1622.4 | 0.167182 | 9895.94ms | 5373214 | 40 | 1.1153e+09 | 3.15846e+06 | 0.29692 | 3.13366 | 15.9048 | 2.91967 | 0.00493311 | 0.0411465 | 5.87079e-05 | 5(Loss) | true |
