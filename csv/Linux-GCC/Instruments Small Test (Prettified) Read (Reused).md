
----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4260.8 | 0.0851471 | 900.931ms | 7932 | 1280 | 2925.05 | 1775.38 | 0.0467111 | 1.23928 | 5.2466 | 1.03013 | 0.00064592 | 9.55386e-06 | 1.18192e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3531.1 | 0.0539412 | 936.829ms | 7932 | 2560 | 3418.42 | 2142.26 | 0.0935271 | 1.48657 | 6.29198 | 1.02471 | 0.000682609 | 1.23609e-05 | 2.65932e-06 | 2(Loss) | true |
| simdjson (reflection) | 2926.17 | 0.0588977 | 982.678ms | 7932 | 2560 | 5934.76 | 2585.13 | 0.151091 | 1.78752 | 7.69037 | 1.04438 | 0.00047395 | 2.83169e-05 | 7.97797e-06 | 3(Loss) | true |
| Glaze | 2565.58 | 0.0420865 | 1019.43ms | 7932 | 2560 | 3942.04 | 2948.48 | 0.0144916 | 2.03959 | 8.07526 | 1.55648 | 0.00187615 | 1.95509e-05 | 6.20509e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2436.8 | 0.0523935 | 1037.43ms | 7932 | 2560 | 6772.06 | 3104.29 | 0.177842 | 2.14607 | 8.73777 | 1.4231 | 0.000795926 | 2.89571e-05 | 1.1376e-05 | 5(Loss) | true |
