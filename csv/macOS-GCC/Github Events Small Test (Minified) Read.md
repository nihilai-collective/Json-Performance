
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1337.87 | 0.687082 | 124.856ms | 1691 | 2560 | 175598 | 1205.4 | 0.166196 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1305.59 | 1.03221 | 121.534ms | 1691 | 1280 | 208076 | 1235.2 | 0.0972447 | 1(Tie) | true |
| Jsonifier (two-stage) | 1272.33 | 0.518529 | 131.58ms | 1691 | 4890 | 211223 | 1267.49 | 0.915577 | 3(Loss) | true |
| simdjson (ondemand) | 1177.58 | 0.520059 | 138.83ms | 1691 | 4890 | 248038 | 1369.47 | 1.26962 | 4(Loss) | true |
| simdjson (reflection) | 963.129 | 0.823882 | 156.587ms | 1691 | 1280 | 243589 | 1674.4 | 0.191479 | 5(Loss) | true |
