
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17983.3 | 0.066725 | 29.4327ms | 5094 | 640 | 20.794 | 270.141 | 0.0300679 | 0.1248 | 1(Win) | true |
| simdjson (reflection) | 12462.4 | 0.158157 | 41.5176ms | 5094 | 80 | 30.4074 | 389.812 | 0.125217 | 0.184882 | 2(Loss) | true |
| Glaze | 4225.33 | 0.058217 | 118.589ms | 5094 | 80 | 35.8416 | 1149.74 | 0.00108719 | 0.57259 | 3(Loss) | true |
