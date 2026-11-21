
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3074.14 | 0.236093 | 5110.57ms | 1151920 | 640 | 4.55557e+08 | 357354 | 1.18164 | 1(Win) | true |
| Jsonifier (two-stage) | 2475.42 | 0.746625 | 6161.77ms | 1151920 | 160 | 1.7566e+09 | 443786 | 0.0885242 | 2(Loss) | true |
| Glaze | 2175.48 | 0.0616184 | 7092.25ms | 1151920 | 320 | 3.09816e+07 | 504971 | 0.103212 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1491.07 | 1.1498 | 8772.36ms | 1151920 | 30 | 2.15285e+09 | 736758 | 6.10615 | -(Loss) | false |
