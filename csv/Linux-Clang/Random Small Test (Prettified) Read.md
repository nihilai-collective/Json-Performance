
----
### Random Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2847.47 | 0.0428733 | 274.87ms | 8051 | 160 | 213.833 | 2696.44 | 0.107896 | 0.861109 | 1(Win) | true |
| Jsonifier (two-stage) | 2530.32 | 0.272062 | 305.478ms | 8051 | 1280 | 87235.8 | 3034.42 | 0.0735545 | 0.970092 | 2(Loss) | true |
| Glaze | 1692.75 | 0.0702929 | 460.499ms | 8051 | 30 | 304.971 | 4535.83 | 0.221445 | 1.45452 | 3(Loss) | true |
| simdjson (ondemand) | 1385.84 | 0.119899 | 558.237ms | 8051 | 4890 | 215780 | 5540.35 | 0.0537324 | 1.77783 | 4(Loss) | true |
