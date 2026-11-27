
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3155.42 | 0.103931 | 3547.15ms | 108313 | 1280 | 1.48167e+06 | 32735.9 | 0.012063 | 1(Win) | true |
| Jsonifier (two-stage) | 1966.12 | 0.277374 | 5610.69ms | 108313 | 160 | 3.39777e+06 | 52537.7 | 0.0945211 | 2(Loss) | true |
| Glaze | 1630 | 0.120653 | 6672.34ms | 108313 | 1280 | 7.48291e+06 | 63371.4 | 0.021178 | 3(Loss) | true |
| simdjson (ondemand) | 714.848 | 0.0495621 | 7584.95ms | 108313 | 2560 | 1.31303e+07 | 144500 | 0.0621998 | 4(Loss) | true |
