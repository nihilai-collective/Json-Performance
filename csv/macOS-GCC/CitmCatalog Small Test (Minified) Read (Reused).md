
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1580.8 | 0.391789 | 264.97ms | 3223 | 4890 | 283781 | 1944.4 | 0.338498 | 1(Win) | true |
| Jsonifier (two-stage) | 1082.67 | 0.436707 | 350.431ms | 3223 | 2560 | 393506 | 2839 | 0.546486 | 2(Loss) | true |
| Glaze | 1012.3 | 0.309164 | 370.776ms | 3223 | 4890 | 430912 | 3036.35 | 0.963878 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 812.287 | 0.798681 | 449.896ms | 3223 | 320 | 292280 | 3784 | 0.339415 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 798.86 | 0.665546 | 441.54ms | 3223 | 1280 | 839356 | 3847.6 | 1.06115 | 4(Tie) | true |
