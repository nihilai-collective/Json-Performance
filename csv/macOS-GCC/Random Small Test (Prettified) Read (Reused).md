
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2070.22 | 0.391544 | 493.137ms | 8051 | 1280 | 269922 | 3708.8 | 0.311794 | 1(Win) | true |
| Jsonifier (two-stage) | 1815.05 | 0.337114 | 533.93ms | 8051 | 2560 | 520613 | 4230.2 | 1.22517 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1377.87 | 0.563752 | 692.072ms | 8051 | 640 | 631598 | 5572.4 | 0.663149 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1375.89 | 0.539596 | 662.414ms | 8051 | 1280 | 1.16059e+06 | 5580.4 | 0.128857 | 3(Tie) | true |
| simdjson (ondemand) | 1105.26 | 0.335657 | 775.249ms | 8051 | 4890 | 2.65871e+06 | 6946.81 | 0.321215 | 5(Loss) | true |
