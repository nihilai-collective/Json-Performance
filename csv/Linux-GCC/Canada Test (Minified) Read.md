
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14128.9 | 0.0478537 | 8194.84ms | 2251027 | 640 | 3.38343e+06 | 151940 | 0.00499348 | 0.360871 | 1.70348 | 0.0747922 | 0.00139843 | 0.0243022 | 1.98382e-06 | 1(Win) | true |
| simdjson (stage-1) | 11407 | 0.031895 | 5016.06ms | 2251027 | 1280 | 4.61183e+06 | 188196 | 0.047683 | 0.450521 | 2.09408 | 0.0806446 | 0.00144378 | 0.0241193 | 7.26752e-07 | 2(Loss) | true |
