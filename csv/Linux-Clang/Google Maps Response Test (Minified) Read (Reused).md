
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2753.14 | 0.0287389 | 450.417ms | 11812 | 80 | 110.617 | 4091.62 | 0.0610631 | 0.893739 | 1(Win) | true |
| Jsonifier (two-stage) | 2040.68 | 0.0551809 | 596.412ms | 11812 | 40 | 371.138 | 5520.12 | 0.279554 | 1.20744 | 2(Loss) | true |
| Glaze | 1848.68 | 0.176382 | 650.709ms | 11812 | 1280 | 147857 | 6093.43 | 0.056868 | 1.33366 | 3(Loss) | true |
| simdjson (ondemand) | 1022.56 | 0.217128 | 1143.36ms | 11812 | 1280 | 732331 | 11016.2 | 0.0926112 | 2.41476 | 4(Loss) | true |
