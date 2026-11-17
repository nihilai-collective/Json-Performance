
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2105.28 | 0.11288 | 6030.27ms | 2090234 | 80 | 9.13897e+07 | 946859 | 0.0409574 | 2.39988 | 7.80015 | 0.373395 | 0.000336751 | 0.0515156 | 8.40277e-05 | 1(Win) | true |
| Glaze | 1448.91 | 0.0919441 | 8743.08ms | 2090234 | 160 | 2.56021e+08 | 1.3758e+06 | 0.0591507 | 3.4527 | 9.59413 | 0.598214 | 0.0117037 | 0.0701387 | 0.000841326 | 2(Loss) | true |
| simdjson (reflection) | 1045.71 | 0.0852545 | 5976.98ms | 2090326 | 160 | 4.22633e+08 | 1.90636e+06 | 0.0312586 | 4.86956 | 15.154 | 1.43489 | 0.0162659 | 0.0507805 | 0.00107602 | 3(Loss) | true |
