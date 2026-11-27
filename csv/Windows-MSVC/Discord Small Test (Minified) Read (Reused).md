
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1960.18 | 0.691226 | 291.724ms | 4857 | 1280 | 341503 | 2363.05 | 0.0363805 | 1.53683 | 1(Win) | true |
| Glaze | 1754.54 | 0.34459 | 319.76ms | 4857 | 30 | 2482.76 | 2640 | 0.126422 | 1.71894 | 2(Loss) | true |
| Jsonifier (two-stage) | 1347 | 0.16758 | 407.082ms | 4857 | 80 | 2656.65 | 3438.75 | 0.542299 | 2.24453 | 3(Loss) | true |
| simdjson (ondemand) | 1080.56 | 0.216115 | 498.719ms | 4857 | 30 | 2574.71 | 4286.67 | 0.547303 | 2.79986 | 4(Loss) | true |
