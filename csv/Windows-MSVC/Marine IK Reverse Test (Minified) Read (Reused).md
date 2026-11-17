
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 679.044 | 0.464403 | 8865.73ms | 1834197 | 80 | 1.14493e+10 | 2.57601e+06 | 0.11285 | 4.4755 | 1(Win) | true |
| Jsonifier (two-stage) | 592.621 | 0.245734 | 9983.43ms | 1834197 | 160 | 8.41757e+09 | 2.95168e+06 | 0.103353 | 5.12808 | 2(Loss) | true |
| Glaze | 312.366 | 0.399001 | 8825.88ms | 1834197 | 30 | 1.49773e+10 | 5.59993e+06 | 0.0426974 | 9.73012 | 3(Loss) | true |
| simdjson (ondemand) | 187.115 | 0.257606 | 6768.13ms | 1834197 | 40 | 2.31978e+10 | 9.34838e+06 | 0.0554334 | 16.243 | 4(Loss) | true |
