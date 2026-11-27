
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3122.04 | 0.516793 | 155.721ms | 4669 | 4890 | 265652 | 1426.22 | 0.0687777 | 1(Win) | true |
| Jsonifier (two-stage) | 1828.48 | 0.59858 | 257.649ms | 4669 | 1280 | 271972 | 2435.2 | 0.346135 | 2(Loss) | true |
| Glaze | 1495.7 | 1.82846 | 290.322ms | 4669 | 2560 | 7.58526e+06 | 2977 | 0.574444 | 3(Loss) | true |
| simdjson (reflection) | 1426.78 | 0.61371 | 328.711ms | 4669 | 320 | 117384 | 3120.8 | 0.0768443 | 4(Loss) | true |
| simdjson (ondemand) | 1273.29 | 0.415707 | 373.781ms | 4669 | 1280 | 270505 | 3497 | 0.393073 | 5(Loss) | true |
