
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1939.74 | 0.123438 | 194.933ms | 3862 | 160 | 878.931 | 1898.75 | 0.197889 | 1.25919 | 1(Win) | true |
| Glaze | 1056.08 | 0.151849 | 363.826ms | 3862 | 40 | 1121.79 | 3487.5 | 0.0239006 | 2.32866 | 2(Loss) | true |
| Jsonifier (two-stage) | 640.909 | 0.161208 | 577.958ms | 3862 | 30 | 2574.71 | 5746.67 | 0.349243 | 3.83939 | 3(Loss) | true |
| simdjson (ondemand) | 322.042 | 0.0782444 | 1170.62ms | 3862 | 30 | 2402.3 | 11436.7 | 0.0291545 | 7.6716 | 4(Loss) | true |
