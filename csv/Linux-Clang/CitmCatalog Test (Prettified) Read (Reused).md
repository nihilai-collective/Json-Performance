
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4547.93 | 0.0991285 | 7079.56ms | 1151920 | 160 | 9.17349e+06 | 241551 | 0.121589 | 0.544306 | 1(Win) | true |
| Jsonifier | 3616.44 | 0.243631 | 8719.24ms | 1151920 | 40 | 2.19081e+07 | 303767 | 0.466346 | 0.684525 | 2(Loss) | true |
| Glaze | 2742.13 | 0.0827759 | 5807ms | 1151920 | 160 | 1.75953e+07 | 400622 | 0.0211591 | 0.90282 | 3(Loss) | true |
| simdjson (ondemand) | 2687.39 | 0.0803407 | 5653.85ms | 1151920 | 160 | 1.72573e+07 | 408782 | 0.0973762 | 0.921198 | 4(Loss) | true |
