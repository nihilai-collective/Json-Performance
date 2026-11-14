
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2085.9 | 0.106548 | 8262.51ms | 631514 | 320 | 3.02843e+07 | 288729 | 0.0632762 | 1.45689 | 1(Win) | true |
| Glaze | 1938.93 | 0.0795441 | 8840.25ms | 631514 | 1280 | 7.81392e+07 | 310614 | 0.0823796 | 1.56744 | 2(Loss) | true |
| Jsonifier | 1885.52 | 0.138154 | 9017.42ms | 631514 | 160 | 3.11567e+07 | 319412 | 0.0686338 | 1.61185 | 3(Loss) | true |
| simdjson (ondemand) | 1636.97 | 0.126882 | 5054.49ms | 631514 | 640 | 1.39464e+08 | 367910 | 0.298433 | 1.8565 | 4(Loss) | true |
