
----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1957.11 | 0.255496 | 401.266ms | 7932 | 2560 | 249657 | 3865.16 | 0.0868389 | 1.25572 | 1(Win) | true |
| Jsonifier (two-stage) | 1816.22 | 0.0932808 | 441.953ms | 7932 | 160 | 2415.09 | 4165 | 0.448163 | 1.35389 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1419.78 | 0.446403 | 553.5ms | 7932 | 1280 | 724080 | 5327.97 | 0.0586872 | 1.73446 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1410.14 | 0.257806 | 569.577ms | 7932 | 2560 | 489625 | 5364.38 | 0.188225 | 1.74653 | 3(Tie) | true |
