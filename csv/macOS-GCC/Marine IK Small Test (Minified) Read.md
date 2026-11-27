
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 705.284 | 0.138528 | 629.543ms | 4604 | 4890 | 363684 | 6225.46 | 0.226628 | 1(Win) | true |
| Jsonifier (two-stage) | 568.039 | 0.206299 | 838.647ms | 4604 | 1280 | 325474 | 7729.6 | 0.441811 | 2(Loss) | true |
| simdjson (reflection) | 535.418 | 0.891591 | 848.234ms | 4604 | 30 | 160375 | 8200.53 | 0.313152 | 3(Loss) | true |
| Glaze | 449.905 | 0.251139 | 991.422ms | 4604 | 640 | 384446 | 9759.2 | 0.31868 | 4(Loss) | true |
| simdjson (ondemand) | 371.883 | 0.105571 | 1190.52ms | 4604 | 2560 | 397728 | 11806.7 | 0.0703485 | 5(Loss) | true |
