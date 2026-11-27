
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3087.85 | 0.0951583 | 821.786ms | 3370 | 640 | 627.798 | 1040.81 | 0.06715 | 1.7297 | 6.83027 | 1.23027 | 0.000595326 | 3.38464e-05 | 6.02745e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 2362.04 | 0.0967458 | 856.905ms | 3370 | 2560 | 4435.98 | 1360.64 | 0.0818012 | 2.23424 | 9.0914 | 1.40326 | 0.000711239 | 3.18759e-05 | 8.11387e-06 | 2(Loss) | true |
| simdjson (reflection) | 2198.45 | 0.0481264 | 873.026ms | 3370 | 4890 | 2420.49 | 1461.89 | 0.0188747 | 2.37127 | 7.73597 | 1.23473 | 0.00172544 | 4.29023e-05 | 1.12262e-05 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 2140.65 | 0.129772 | 884.178ms | 3370 | 640 | 2429.47 | 1501.36 | 0.243705 | 2.46976 | 10.635 | 2.05519 | 0.000646792 | 4.21921e-05 | 1.25185e-05 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2138.17 | 0.1097 | 895.621ms | 3370 | 80 | 217.509 | 1503.1 | 0.0332757 | 2.47536 | 8.52997 | 1.55935 | 0.00114614 | 0.000107567 | 3.7092e-05 | 4(Tie) | true |
