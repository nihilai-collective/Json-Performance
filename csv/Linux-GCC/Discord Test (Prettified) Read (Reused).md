
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3277.94 | 0.216004 | 3519.11ms | 83958 | 40 | 111354 | 24426.5 | 0.206486 | 1.52406 | 7.41654 | 1.1339 | 0.00168686 | 2.17371e-05 | 1.63772e-05 | 1(Win) | true |
| Glaze | 3235.14 | 0.0434584 | 3563.86ms | 83958 | 2560 | 296160 | 24749.7 | 0.105181 | 1.56237 | 8.47109 | 1.7268 | 0.00213133 | 1.40463e-05 | 8.83068e-06 | 2(Loss) | true |
| Jsonifier | 2772.58 | 0.0642073 | 3985.25ms | 83958 | 1280 | 440083 | 28878.7 | 0.124335 | 1.81474 | 7.54458 | 1.52686 | 0.00359582 | 2.27699e-05 | 1.35764e-05 | 3(Loss) | true |
| simdjson (reflection) | 2558.24 | 0.0732029 | 4245.86ms | 83958 | 2560 | 1.34381e+06 | 31298.3 | 0.0675663 | 1.9745 | 8.69522 | 1.39963 | 0.00228901 | 2.29467e-05 | 1.38043e-05 | 4(Loss) | true |
| simdjson (ondemand) | 2325.78 | 0.0206066 | 4568.32ms | 83958 | 4890 | 246098 | 34426.6 | 0.171122 | 2.17391 | 9.09032 | 1.56113 | 0.00569353 | 1.99657e-05 | 1.2091e-05 | 5(Loss) | true |
