
----
### Github Events Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 924.224 | 0.0176818 | 6235.74ms | 53331 | 4890 | 462983 | 55030.4 | 0.0228204 | 5.57312 | 19.7618 | 3.93655 | 0.0168654 | 5.46573e-05 | 2.1481e-05 | 1(Win) | true |
| simdjson (ondemand) | 477.266 | 0.122058 | 5829.58ms | 53331 | 320 | 5.414e+06 | 106566 | 0.0234717 | 10.6815 | 36.9715 | 7.4847 | 0.0728881 | 9.12345e-05 | 5.15648e-05 | 2(Loss) | true |
