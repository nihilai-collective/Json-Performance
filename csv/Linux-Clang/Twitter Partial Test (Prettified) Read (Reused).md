
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 11892.3 | 0.243275 | 5239.06ms | 631514 | 160 | 2.42855e+06 | 50642.6 | 0.0857607 | 0.208043 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 11860.5 | 0.0653855 | 5166.02ms | 631514 | 4890 | 5.39057e+06 | 50778.6 | 0.207834 | 0.208608 | 1(Tie) | true |
| simdjson (ondemand) | 9729.87 | 0.12149 | 6241.6ms | 631514 | 640 | 3.61923e+06 | 61897.9 | 0.00785758 | 0.254328 | 3(Loss) | true |
| Glaze | 4279.38 | 0.059213 | 7220.79ms | 631514 | 1280 | 8.88893e+06 | 140735 | 0.062644 | 0.578439 | 4(Loss) | true |
