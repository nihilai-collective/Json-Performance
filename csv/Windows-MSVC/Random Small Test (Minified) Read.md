
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 971.444 | 0.0922792 | 504.616ms | 5094 | 2560 | 54516.7 | 5000.82 | 0.254511 | 3.1173 | 1(Win) | true |
| Jsonifier (two-stage) | 852.225 | 0.0818808 | 576.086ms | 5094 | 2560 | 55771.6 | 5700.39 | 0.269265 | 3.55278 | 2(Loss) | true |
| Glaze | 704.825 | 0.0604994 | 692.547ms | 5094 | 4890 | 85028.9 | 6892.52 | 0.0903738 | 4.29775 | 3(Loss) | true |
| simdjson (ondemand) | 553.778 | 0.064212 | 881.967ms | 5094 | 4890 | 155163 | 8772.49 | 0.0561325 | 5.47373 | 4(Loss) | true |
