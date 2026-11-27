
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2193.07 | 0.136098 | 181.469ms | 3770 | 2560 | 12744.5 | 1639.41 | 0.00238265 | 1.36896 | 1(Win) | true |
| simdjson (ondemand) | 1757.04 | 0.136424 | 232.12ms | 3770 | 320 | 2493.73 | 2046.25 | 0.0305344 | 1.71512 | 2(Loss) | true |
