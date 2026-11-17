
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1682.56 | 0.0544947 | 328.841ms | 5094 | 40 | 99.025 | 2887.28 | 0.263394 | 1.45745 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 1590.67 | 0.13098 | 350.858ms | 5094 | 40 | 640.071 | 3054.07 | 0.127263 | 1.54319 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1590.38 | 0.0848685 | 354.217ms | 5094 | 30 | 201.62 | 3054.63 | 0.421615 | 1.54412 | 2(Tie) | true |
| Jsonifier (two-stage) | 1556.22 | 0.0824838 | 357.153ms | 5094 | 80 | 530.399 | 3121.68 | 0.0320443 | 1.57744 | 4(Loss) | true |
| Glaze | 1460.9 | 0.0683932 | 378.894ms | 5094 | 80 | 413.804 | 3325.36 | 0.0944397 | 1.68138 | 5(Loss) | true |
