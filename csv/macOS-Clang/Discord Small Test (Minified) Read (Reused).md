
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2614.94 | 0.0713872 | 192.358ms | 4857 | 320 | 511.685 | 1771.36 | 0.00105852 | 1(Win) | true |
| Jsonifier (two-stage) | 1868.18 | 0.0715246 | 257.197ms | 4857 | 160 | 503.188 | 2479.42 | 0.033011 | 2(Loss) | true |
| Glaze | 1836.16 | 0.150152 | 270.784ms | 4857 | 320 | 4591.25 | 2522.66 | 0.0516301 | 3(Loss) | true |
| simdjson (ondemand) | 608.263 | 0.308449 | 758.666ms | 4857 | 2560 | 1.41241e+06 | 7615.12 | 0.140281 | 4(Loss) | true |
