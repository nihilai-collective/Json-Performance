
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3380.3 | 0.0901019 | 138.533ms | 4669 | 40 | 56.3462 | 1317.25 | 0.0468366 | 0.718205 | 1(Win) | true |
| Jsonifier (two-stage) | 2456.89 | 0.318593 | 186.75ms | 4669 | 1280 | 42673.5 | 1812.34 | 0.0321908 | 0.99314 | 2(Loss) | true |
| Glaze | 1834.44 | 0.0435508 | 250.574ms | 4669 | 80 | 89.3973 | 2427.29 | 0.0344916 | 1.33491 | 3(Loss) | true |
| simdjson (ondemand) | 645.87 | 0.0957686 | 697.328ms | 4669 | 4890 | 213164 | 6894.12 | 0.044148 | 3.81773 | 4(Loss) | true |
