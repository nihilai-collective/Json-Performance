
----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18632 | 0.0776244 | 4453.14ms | 716365 | 80 | 64809.4 | 36667.1 | 0.033147 | 0.271451 | 0.751061 | 0.0922044 | 0.000176603 | 0.0038969 | 1.60358e-05 | 1(Win) | true |
| Glaze | 5109.06 | 0.106826 | 7285.69ms | 716365 | 2560 | 5.22373e+07 | 133719 | 0.0373857 | 0.985299 | 2.70587 | 0.438066 | 0.000356153 | 0.0480719 | 5.48396e-06 | 2(Loss) | true |
| simdjson (reflection) | 536.711 | 0.230217 | 8050.04ms | 716365 | 320 | 2.74797e+09 | 1.2729e+06 | 0.253113 | 9.4455 | 30.5385 | 6.83028 | 0.0701844 | 0.29354 | 0.00129595 | 3(Loss) | true |
