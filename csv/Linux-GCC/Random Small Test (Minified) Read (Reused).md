
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2304.67 | 0.12403 | 253.948ms | 5094 | 30 | 205.059 | 2107.9 | 0.0126492 | 1.06144 | 1(Win) | true |
| Jsonifier (two-stage) | 1793.91 | 0.0978261 | 306.706ms | 5094 | 30 | 210.547 | 2708.07 | 0.370636 | 1.36668 | 2(Loss) | true |
| simdjson (ondemand) | 1551.14 | 0.47021 | 358.58ms | 5094 | 1280 | 277595 | 3131.91 | 0.00895441 | 1.58289 | 3(Loss) | true |
| simdjson (reflection) | 1486.39 | 0.0834169 | 373.78ms | 5094 | 30 | 222.989 | 3268.33 | 0.142581 | 1.65333 | 4(Loss) | true |
| Glaze | 1337.47 | 0.0466314 | 403.303ms | 5094 | 160 | 459.016 | 3632.24 | 0.469771 | 1.83756 | 5(Loss) | true |
