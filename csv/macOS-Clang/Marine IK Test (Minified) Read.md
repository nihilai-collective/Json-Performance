
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 618.08 | 1.52756 | 8730.14ms | 1834197 | 40 | 7.47585e+10 | 2.8301e+06 | 7.66985 | -(Win) | false |
| Jsonifier (two-stage) | 495.519 | 0.806752 | 5209.28ms | 1834197 | 80 | 6.48845e+10 | 3.53009e+06 | 1.33329 | 2(Loss) | true |
| Glaze | 404.758 | 0.483974 | 6201.22ms | 1834197 | 80 | 3.49972e+10 | 4.32166e+06 | 1.4776 | 3(Loss) | true |
| simdjson (ondemand) | 372.639 | 0.634936 | 6968.88ms | 1834197 | 40 | 3.55332e+10 | 4.69415e+06 | 0.928915 | 4(Loss) | true |
