
----
### Random Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14649.1 | 0.109196 | 35.8079ms | 5094 | 80 | 10.4905 | 331.625 | 0.037679 | 0.155654 | 1(Win) | true |
| Glaze | 3356.32 | 0.227194 | 146.503ms | 5094 | 40 | 432.558 | 1447.42 | 0.0259014 | 0.724602 | 2(Loss) | true |
