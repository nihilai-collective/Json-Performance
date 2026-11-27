
----
### Canada Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6108.12 | 0.0327948 | 6600.37ms | 6661989 | 320 | 3.72352e+07 | 1.04015e+06 | 0.254739 | 0.827813 | 2.48933 | 0.117136 | 0.000103562 | 0.0280004 | 5.44812e-05 | 1(Win) | true |
| Glaze | 3953.93 | 0.107708 | 5020.97ms | 6661897 | 30 | 8.9858e+07 | 1.60683e+06 | 0.00531303 | 1.28116 | 4.33307 | 0.464028 | 0.00373031 | 0.0248209 | 6.23846e-05 | 2(Loss) | true |
| simdjson (reflection) | 443.771 | 0.392312 | 10132.3ms | 6661989 | 30 | 9.46398e+10 | 1.43168e+07 | 0.0868034 | 11.3872 | 36.3409 | 4.85387 | 0.0134874 | 0.255256 | 0.0986744 | 3(Loss) | true |
