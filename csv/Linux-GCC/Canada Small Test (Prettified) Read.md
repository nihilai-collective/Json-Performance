
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1873.04 | 0.0691294 | 582.747ms | 11579 | 40 | 664.408 | 5895.55 | 0.0132886 | 1.31543 | 1(Win) | true |
| Jsonifier | 1789.18 | 0.409658 | 606.923ms | 11579 | 640 | 409124 | 6171.86 | 0.0939372 | 1.37765 | 2(Loss) | true |
| simdjson (reflection) | 1648.71 | 0.114541 | 681.302ms | 11579 | 30 | 1765.6 | 6697.7 | 0.095148 | 1.49531 | 3(Loss) | true |
| simdjson (ondemand) | 1618.15 | 0.0860828 | 686.296ms | 11579 | 40 | 1380.38 | 6824.23 | 0.025284 | 1.5238 | 4(Loss) | true |
| Glaze | 1553.08 | 0.115472 | 724.874ms | 11579 | 4890 | 329620 | 7110.11 | 0.0215429 | 1.58826 | 5(Loss) | true |
