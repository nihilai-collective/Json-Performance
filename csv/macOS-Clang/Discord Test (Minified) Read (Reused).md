
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2864.76 | 1.07631 | 2164.63ms | 56369 | 80 | 3.26338e+06 | 18765.1 | 0.337262 | 1(Win) | true |
| Glaze | 1596.28 | 0.277425 | 3599.48ms | 56369 | 4890 | 4.26838e+07 | 33676.9 | 2.17452 | 2(Loss) | true |
| Jsonifier (two-stage) | 1417.04 | 1.27965 | 4653.78ms | 56369 | 80 | 1.88534e+07 | 37936.5 | 0.0384672 | 3(Loss) | true |
| simdjson (ondemand) | 728.799 | 0.789921 | 7935.38ms | 56369 | 160 | 5.43191e+07 | 73762 | 0.0402654 | 4(Loss) | true |
