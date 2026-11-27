
----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10124.6 | 0.856917 | 50.159ms | 4857 | 160 | 2459.12 | 457.5 | 0.813008 | 0.229427 | 1(Win) | true |
| Glaze | 3474.54 | 0.28778 | 150.343ms | 4857 | 160 | 2354.95 | 1333.12 | 0.0469043 | 0.697141 | 2(Loss) | true |
