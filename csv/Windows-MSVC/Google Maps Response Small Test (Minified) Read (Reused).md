
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1355.07 | 0.421873 | 375.761ms | 4390 | 1280 | 217460 | 3089.61 | 0.869805 | 2.23008 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1147.69 | 0.13084 | 430.164ms | 4390 | 1280 | 29159 | 3647.89 | 0.657419 | 2.63361 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1142.33 | 0.301912 | 442.08ms | 4390 | 40 | 4897.44 | 3665 | 0.22686 | 2.64727 | 2(Tie) | true |
| simdjson (ondemand) | 666.503 | 1.31139 | 695.012ms | 4390 | 2560 | 1.7371e+07 | 6281.48 | 2.05758 | 4.54523 | 4(Loss) | true |
