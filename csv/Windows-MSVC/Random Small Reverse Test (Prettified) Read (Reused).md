
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 957.897 | 0.0525337 | 888.919ms | 8150 | 4890 | 88850.9 | 8114.07 | 0.15085 | 3.16506 | 1(Win) | true |
| simdjson (ondemand) | 639.017 | 0.264309 | 1375.1ms | 8150 | 160 | 165361 | 12163.1 | 1.72205 | 4.74958 | 2(Loss) | true |
