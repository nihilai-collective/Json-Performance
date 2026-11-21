
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 992.393 | 0.235041 | 483.33ms | 4857 | 40 | 4814.1 | 4667.5 | 0.232641 | 2.4758 | 1(Win) | true |
| Jsonifier (two-stage) | 795.192 | 0.236313 | 601.291ms | 4857 | 2560 | 485072 | 5825 | 0.233915 | 3.09762 | 2(Loss) | true |
| Glaze | 773.737 | 0.189216 | 609.927ms | 4857 | 4890 | 627446 | 5986.52 | 0.32798 | 3.18466 | 3(Loss) | true |
| simdjson (ondemand) | 721.442 | 0.468725 | 667.275ms | 4857 | 640 | 579627 | 6420.47 | 0.0121666 | 3.41891 | 4(Loss) | true |
