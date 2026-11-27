
----
### Discord Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 8934.53 | 0.418798 | 56.6864ms | 4857 | 320 | 1508.52 | 518.438 | 0.180505 | 0.262441 | 1(Win) | true |
| Glaze | 2881.26 | 0.349697 | 166.012ms | 4857 | 4890 | 154548 | 1607.63 | 0.339555 | 0.843482 | 2(Loss) | true |
