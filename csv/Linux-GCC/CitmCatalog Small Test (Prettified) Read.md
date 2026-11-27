
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2699.13 | 0.114474 | 929.764ms | 5839 | 1280 | 7139.27 | 2063.08 | 0.0821821 | 1.95779 | 7.84364 | 1.45008 | 0.000589918 | 4.04072e-05 | 1.61896e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2445.39 | 0.050512 | 951.872ms | 5839 | 320 | 423.369 | 2277.14 | 0.296615 | 2.14463 | 8.73574 | 1.39544 | 0.000611192 | 2.03374e-05 | 1.07039e-06 | 2(Loss) | true |
| simdjson (reflection) | 2172.48 | 0.0450883 | 981.356ms | 5839 | 4890 | 6531.31 | 2563.2 | 0.18207 | 2.40018 | 8.99452 | 1.46224 | 0.000604881 | 4.89271e-05 | 1.56553e-05 | 3(Loss) | true |
| simdjson (ondemand) | 2127.25 | 0.051916 | 984.749ms | 5839 | 4890 | 9031.29 | 2617.7 | 0.0968729 | 2.45407 | 9.23549 | 1.53691 | 0.00103052 | 5.13436e-05 | 1.55502e-05 | 4(Loss) | true |
| Glaze | 1796.11 | 0.0810609 | 1030.52ms | 5839 | 4890 | 30884.6 | 3100.31 | 0.0454112 | 2.8967 | 11.2009 | 2.14044 | 0.0017239 | 7.84864e-05 | 3.67391e-05 | 5(Loss) | true |
