
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9057.42 | 0.111854 | 7405.55ms | 631514 | 80 | 442534 | 66493.4 | 0.0448715 | 0.559868 | 2.72586 | 0.284228 | 0.000586943 | 1.61517e-05 | 1.29253e-05 | 1(Win) | true |
| Jsonifier | 9031.48 | 0.0280954 | 7431.99ms | 631514 | 4890 | 1.71644e+06 | 66684.4 | 0.00319107 | 0.560272 | 2.72767 | 0.284694 | 0.000605416 | 1.63181e-05 | 1.33286e-05 | 2(Loss) | true |
| simdjson (reflection) | 8328.03 | 0.0231462 | 7977.24ms | 631514 | 4890 | 1.37009e+06 | 72317 | 0.0108804 | 0.605702 | 3.00657 | 0.289437 | 0.000636591 | 5.21841e-06 | 3.71879e-06 | 3(Loss) | true |
| simdjson (ondemand) | 8177.31 | 0.0173869 | 8112.58ms | 631514 | 4890 | 801863 | 73650 | 0.0700545 | 0.617842 | 3.02993 | 0.289906 | 0.000564442 | 3.96392e-06 | 2.57019e-06 | 4(Loss) | true |
| Glaze | 3846.3 | 0.0480348 | 8381.48ms | 631514 | 1280 | 7.24105e+06 | 156581 | 0.107847 | 1.31484 | 5.8562 | 0.962311 | 0.00140501 | 2.04741e-05 | 1.77314e-05 | 5(Loss) | true |
