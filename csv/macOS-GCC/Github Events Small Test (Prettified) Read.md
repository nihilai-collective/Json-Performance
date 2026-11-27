
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1683.6 | 1.35325 | 128.611ms | 2158 | 640 | 175132 | 1222.4 | 0.0654879 | 1(Win) | true |
| Glaze | 1594.14 | 0.526989 | 130.791ms | 2158 | 4890 | 226340 | 1290.99 | 0.062404 | 2(Loss) | true |
| Jsonifier (two-stage) | 1505.29 | 1.03474 | 142.323ms | 2158 | 1280 | 256174 | 1367.2 | 0.116891 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1409.52 | 0.518752 | 149.269ms | 2158 | 4890 | 280536 | 1460.09 | 0.267132 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1392.91 | 0.697073 | 149.486ms | 2158 | 2560 | 271551 | 1477.5 | 0.114927 | 4(Tie) | true |
