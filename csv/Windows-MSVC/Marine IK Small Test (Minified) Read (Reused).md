
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 606.872 | 0.105565 | 849.927ms | 4604 | 40 | 2333.33 | 7235 | 0.0230309 | 5.00799 | 1(Win) | true |
| Jsonifier (two-stage) | 521.872 | 0.0737663 | 968.803ms | 4604 | 2560 | 98605.1 | 8413.4 | 0.05893 | 5.80897 | 2(Loss) | true |
| simdjson (ondemand) | 292.607 | 0.0452716 | 1599.8ms | 4604 | 4890 | 225664 | 15005.5 | 0.141843 | 10.3723 | 3(Loss) | true |
| Glaze | 289.255 | 0.120757 | 1629.73ms | 4604 | 640 | 215036 | 15179.4 | 0.255934 | 10.4929 | 4(Loss) | true |
