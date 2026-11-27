
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 847.093 | 0.109377 | 981.824ms | 7932 | 30 | 2862.07 | 8930 | 0.851221 | 3.58072 | 1(Win) | true |
| simdjson (ondemand) | 308.793 | 0.882327 | 2419.35ms | 7932 | 4890 | 2.28454e+08 | 24497.2 | 1.12832 | 9.83433 | 2(Loss) | true |
