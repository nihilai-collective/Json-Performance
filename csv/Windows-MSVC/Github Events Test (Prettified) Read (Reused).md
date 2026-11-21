
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1649.27 | 0.16628 | 4503.41ms | 65103 | 4890 | 1.91606e+07 | 37645.3 | 1.20069 | 1.49986 | 1(Win) | true |
| Glaze | 1603.84 | 0.114076 | 4661.3ms | 65103 | 2560 | 4.99237e+06 | 38711.4 | 0.171027 | 1.54263 | 2(Loss) | true |
| Jsonifier | 1420.78 | 0.224554 | 5079.82ms | 65103 | 1280 | 1.23254e+07 | 43699.3 | 0.328419 | 1.74142 | 3(Loss) | true |
| simdjson (ondemand) | 987.94 | 0.665018 | 7046.63ms | 65103 | 40 | 6.98664e+06 | 62845 | 0.172679 | 2.50518 | 4(Loss) | true |
