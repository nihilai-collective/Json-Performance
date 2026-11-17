
----
### Google Maps Response Test (Prettified) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13365.9 | 0.0803067 | 907.428ms | 25388 | 1280 | 2708.76 | 1811.46 | 0.00258762 | 0.387704 | 1.91386 | 0.15917 | 4.91128e-05 | 6.12371e-06 | 3.38497e-07 | 1(Win) | true |
| simdjson (stage-1) | 12776.9 | 0.0655224 | 917.467ms | 25388 | 40 | 61.666 | 1894.97 | 0.00395799 | 0.404181 | 1.96975 | 0.0766504 | 9.45329e-05 | 5.9083e-06 | 0 | 2(Loss) | true |
