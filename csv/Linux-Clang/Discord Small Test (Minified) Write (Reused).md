
----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13559.8 | 0.144655 | 37.0463ms | 4857 | 320 | 78.1348 | 341.597 | 0.126999 | 0.168646 | 1(Win) | true |
| Glaze | 4279.87 | 0.326193 | 110.671ms | 4857 | 2560 | 31905.5 | 1082.28 | 0.0493273 | 0.564623 | 2(Loss) | true |
