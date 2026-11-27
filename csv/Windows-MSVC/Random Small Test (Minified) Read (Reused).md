
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1092.51 | 0.208338 | 573.525ms | 5094 | 30 | 2574.71 | 4446.67 | 0.0749064 | 2.25376 | 1(Win) | true |
| Jsonifier (two-stage) | 914.536 | 0.202825 | 650.766ms | 5094 | 4890 | 567635 | 5312 | 0.361002 | 2.69311 | 2(Loss) | true |
| Glaze | 802.398 | 0.581105 | 720.083ms | 5094 | 320 | 396094 | 6054.38 | 0.560573 | 3.07097 | 3(Loss) | true |
| simdjson (ondemand) | 499.915 | 0.149966 | 1127.58ms | 5094 | 4890 | 1.03854e+06 | 9717.69 | 0.0349206 | 4.93817 | 4(Loss) | true |
