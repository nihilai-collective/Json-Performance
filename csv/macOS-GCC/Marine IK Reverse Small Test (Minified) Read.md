
----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 645.736 | 0.114533 | 686.068ms | 4604 | 4890 | 296574 | 6799.55 | 0.520132 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 533.009 | 0.247872 | 845.683ms | 4604 | 640 | 266830 | 8237.6 | 0.145886 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 531.435 | 0.183125 | 873.716ms | 4604 | 1280 | 293006 | 8262 | 0.390625 | 2(Tie) | true |
| Glaze | 449.059 | 0.168592 | 987.588ms | 4604 | 1280 | 347815 | 9777.6 | 0.0735835 | 4(Loss) | true |
| simdjson (ondemand) | 387.783 | 0.182016 | 1151.1ms | 4604 | 1280 | 543653 | 11322.6 | 0.0583245 | 5(Loss) | true |
