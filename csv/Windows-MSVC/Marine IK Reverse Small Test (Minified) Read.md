
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 413.177 | 0.101645 | 1068.5ms | 4604 | 1280 | 149340 | 10626.7 | 0.0632651 | 7.34034 | 1(Win) | true |
| Jsonifier (two-stage) | 406.054 | 0.147266 | 1100.55ms | 4604 | 320 | 81143.8 | 10813.1 | 0.017337 | 7.46081 | 2(Loss) | true |
| Glaze | 254.391 | 0.0485457 | 1732.36ms | 4604 | 2560 | 179726 | 17259.7 | 0.143013 | 11.932 | 3(Loss) | true |
| simdjson (ondemand) | 144.263 | 0.0304644 | 3047.44ms | 4604 | 4890 | 420389 | 30435.4 | 0.0890495 | 21.0525 | 4(Loss) | true |
