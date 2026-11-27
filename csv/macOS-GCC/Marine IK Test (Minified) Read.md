
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 601.047 | 0.44058 | 9034.95ms | 1834197 | 160 | 2.63054e+10 | 2.9103e+06 | 3.91016 | 1(Win) | true |
| Glaze | 473.1 | 0.329462 | 5524.26ms | 1834197 | 30 | 4.45162e+09 | 3.69737e+06 | 0.281008 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 452.301 | 1.10795 | 5521.17ms | 1834197 | 40 | 7.34405e+10 | 3.8674e+06 | 0.013954 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 442.949 | 0.801263 | 5971.7ms | 1834197 | 40 | 4.00492e+10 | 3.94904e+06 | 0.353574 | 3(Tie) | true |
| simdjson (ondemand) | 383.504 | 0.598352 | 6987.81ms | 1834197 | 80 | 5.95876e+10 | 4.56117e+06 | 2.99046 | 5(Loss) | true |
